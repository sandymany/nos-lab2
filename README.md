# Labos - naprave

## a) Operacija `poll`

Prvi dio zadatka (rješenje u folderu lab2a) vezan je uz implementaciju naprave te korištenje operacije `poll(struct pollfd *fds, nfds_t nfds, int timeout)`.
Operacija `poll()` koristi se za praćenje više file deskriptora kako bi se utvrdilo je li moguće izvršiti I/O operaciju na bilo kojoj od njih. `poll()` omogućuje programima da efikasno čekaju na događaje na više file deskriptora istovremeno bez potrebe za radnim čekanjem.

### Pokretanje:
- `$cd lab2a`
- `$make`
- `$sudo ./load_shofer`
- `$tail /var/log/kern.log`
- `$cd rjesenja`
- `$gcc -o writer.out writer.c`
- `$gcc -o reader.out reader.c`
- `$./writer.out`
- `$./reader.out`

Stvoreno je više naprava i međuspremnika te program `reader.c` (čeka kad bilo koja naprava bude spremna za pisanje) i `writer.c` (čeka kad bilo koja naprava bude spremna za čitanje). `reader` upisuje random generirani znak u međuspremnik naprave `/dev/shofer` te ga zatim `writer` kada dođe na red čita.


## b) Operacija `ioctl`

Operacija `ioctl(int fd, unsigned long request, ...)` (I/O control) koristi se za prilagođavanje ponašanja naprava specifičnim akcijama koje ne odgovaraju standardnim operacijama čitanja i pisanja. Ova operacija pruža sučelje za komunikaciju između korisničkog prostora i jezgre.

### Pokretanje:
- `$cd lab2b`
- `$make`
- `$sudo ./load_shofer`
- `$tail /var/log/kern.log`
- `$cd rjesenja`
- `$gcc -o ioctl.out ioctl.c`
- `$./ioctl.out /dev/shofer_control $number_of_bytes`

Radnoj napravi `shofer_control` šaljemo naredbu `ioctl()` u kojoj definiramo broj bajtova koje je potrebno prepisati iz izlazne u ulaznu napravu.

## c) Red poruka

U ovom dijelu zadatka bilo je potrebano ostvariti red poruka pomoću naprava.
