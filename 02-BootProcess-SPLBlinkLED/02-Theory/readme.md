## Boot Process

![alt text](image.png)

- VDK STM32F1 có 2 jumper cho phép người sử dụng lựa chọn nơi thực thi chương trình sau khi Reset

- Thông thường BOOT1 = BOOT0 = 0 -> sau khi khởi động, VDK tìm đến vùng nhớ Flash và chạy nó

- Mỗi khi CPU reset, PC nhảy đến địa chỉ bắt đầu (với boot 0-0 là thực thi vùng nhớ tại Flash, PC-> 0x08000000) , đây là vị trí lưu chương trình bootloader. vì vậy chương trình này sẽ được chạy đầu tiên.

Reset → Load SP → Load PC → Reset_Handler → SystemInit() → init
.data/.bss → main()

- Nạp giá trị ô nhớ đầu tiên của VTOR vào MSP

- Lấy địa chỉ của Reset_Handler được đặt trong ô nhớ thứ 2 của VTOR, load vào PC để thực hiện (systemint() -> khởi tạo data/bss -> chạy main())

## Build, Flash & Debug trên VsCode và sử dụng bare-metal, thư viện SPL

- Sau khi cài GNU - ARM & OpenOCD, viết makefile để build chương trình bare - metal, cài tiếp 1 số thứ sau để sử dụng được thư viện SPL & Debug

- Tải thư viện SPL cho STM32F1: https://www.st.com/en/embedded-software/stsw-stm32054.html

- Lấy đường dẫn thư viện để dùng, file `c_cpp_properties.json`

```c
{
    "configurations": [
        {
            "name": "STM32",
            "includePath": [
                "${workspaceFolder}/SPL/inc",
                "${workspaceFolder}/Core",
                "E:/GNUARM/10 2021.10/arm-none-eabi/include",
                "E:/SPLib/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/STM32F10x_StdPeriph_Driver/inc",
                "E:/SPLib/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x",
                "E:/SPLib/STM32F10x_StdPeriph_Lib_V3.6.0/Libraries/CMSIS/CM3/CoreSupport"
            ],
            "defines": [
                "STM32F10X_MD",
                "USE_STDPERIPH_DRIVER"
            ],
            "compilerPath": "E:/GNUARM/10 2021.10/bin/arm-none-eabi-gcc.exe",
            "cStandard": "c11",
            "intelliSenseMode": "gcc-arm"
        }
    ],
    "version": 4
}
```

- File cấu hình openOCD để debug `launch.json`

```c
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Debug (OpenOCD)",
      "type": "cortex-debug",
      "request": "launch",
      "servertype": "openocd",
      "cwd": "${workspaceFolder}",
      "executable": "${workspaceFolder}/blinkled.elf",
      "device": "STM32F103C8Tx",
      "configFiles": [
        "E:/OpenOCD/xpack-openocd-0.12.0-6/openocd/scripts/interface/stlink.cfg",
        "E:/OpenOCD/xpack-openocd-0.12.0-6/openocd/scripts/target/stm32f1x.cfg"
      ],
      "runToEntryPoint": "main",
      "preLaunchTask": "Build STM32",
      "svdFile": "${workspaceFolder}/STM32F103.svd"
    }
  ]
}
```
- File `tasks.json`

```c
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build STM32",
            "type": "shell",
            "command": "make",
            "args": [],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": [
                "$gcc"
            ]
        },
        {
            "label": "Flash STM32",
            "type": "shell",
            "command": "openocd",
            "args": [
                "-f",
                "interface/stlink.cfg",
                "-f",
                "target/stm32f1x.cfg",
                "-c",
                "program build/test.elf verify reset exit"
            ],
            "group": {
                "kind": "none"
            },
            "problemMatcher": []
        },
        {
            "label": "Clean STM32",
            "type": "shell",
            "command": "make",
            "args": [
                "clean"
            ],
            "group": {
                "kind": "build"
            },
            "problemMatcher": []
        }
    ]
}
```
- Tải file System View Description để thấy các thanh ghi, extension Cortex Debug trong VsCode
 `STM32F1.svd`
https://www.st.com/en/microcontrollers-microprocessors/stm32f103.html#cad-resources

