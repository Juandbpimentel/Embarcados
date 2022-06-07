# Boot da beagle bone black

## Settar o ambiente de de envio de dados

    setenv autoload no;setenv ipaddr 10.4.1.2; setenv serverip 10.4.1.1;

## Enviar arquivo para a placa

    tftp 0x80000000 /tftpboot/download.bin

## Bootar a placa

    echo "***Booting to BareMetal ***";go 0x80000000

## Código total

    setenv autoload no;setenv ipaddr 10.4.1.2; setenv serverip 10.4.1.1;tftp 0x80000000 /tftpboot/download.bin;echo "***Booting to BareMetal ***";go 0x80000000;
