# Boot da beagle bone black



## Código de boot padrão

    setenv app "mw 0x44e35048 0xaaaa; sleep 1; mw 0x44e35048 0x5555;setenv ipaddr 10.4.1.2; setenv serverip 10.4.1.1; tftp 0x80000000 /tftpboot/download.bin; echo "***Booting to BareMetal ***";go 0x80000000;"






## Settar o ambiente de de envio de dados

    mw 0x44e35048 0xaaaa; sleep 1; mw 0x44e35048; setenv autoload no;setenv ipaddr 10.4.1.2; setenv serverip 10.4.1.1;

## Enviar arquivo para a placa

    tftp 0x80000000 /tftpboot/download.bin

## Bootar a placa

    echo "***Booting to BareMetal ***";go 0x80000000







## Código inteiro de boot com Watchdog e pelo cabo de rede

    setenv app "autoload no;setenv ipaddr 10.4.1.2; setenv serverip 10.4.1.1; tftp 0x80000000 /tftpboot/download.bin; echo "***Booting to BareMetal ***";go 0x80000000;"

## Código de boot sem Watchdog e pelo cabo de rede

    setenv app "mw 0x44e35048 0xaaaa; sleep 1; mw 0x44e35048 0x5555;setenv ipaddr 10.4.1.2; setenv serverip 10.4.1.1; tftp 0x80000000 /tftpboot/download.bin; echo "***Booting to BareMetal ***";go 0x80000000;"

## Código de boot com Watchdog e sem cabo de rede

    setenv ipaddr 10.4.1.2; setenv serverip 10.4.1.1;setenv ethact usb_ether; setenv usbnet_devaddr f8:dc:7a:00:00:02; setenv usbnet_hostaddr f8:dc:7a:00:00:01; tftp 0x80000000 /tftpboot/download.bin; echo "***Booting to BareMetal ***";go 0x80000000;

## Código de boot sem Watchdog e sem cabo de rede

    set app "mw 0x44e35048 0xaaaa; sleep 1; mw 0x44e35048 0x5555;setenv ipaddr 10.4.1.2; setenv serverip 10.4.1.1;setenv ethact usb_ether; setenv usbnet_devaddr f8:dc:7a:00:00:02; setenv usbnet_hostaddr f8:dc:7a:00:00:01;tftp 0x80000000 appGpio.bin;echo *** Booting to BareMetal ***;go 0x80000000"
