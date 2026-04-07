# MCU
MCU = atmega32u4
BOOTLOADER = caterina

# Split keyboard support
SPLIT_KEYBOARD = yes

# Features
MOUSEKEY_ENABLE = no       # Mouse key support (disabled to save space)
EXTRAKEY_ENABLE = yes      # Audio control and System control
CONSOLE_ENABLE = yes       # Enable qmk console for matrix debugging (disable after confirmed working)
COMMAND_ENABLE = no        # Disable command mode
NKRO_ENABLE = no           # Pro Micro does not support USB NKRO
BACKLIGHT_ENABLE = no
AUDIO_ENABLE = no
