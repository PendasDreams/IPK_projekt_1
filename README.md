IPK_projekt_1


TODO:<br /> 
testy ***<br />
dokumentace v readme: je to jen na linux, + co ma obsahovat je na ipk  <br />
changelog.md: implementace funkcionalita a limitace <br />
git + přidat jim pristup + snapshot <br />
zazipovat <br />




## Client pro IPK Calculator protocol

ipkcp je jednoduchý client, který dokáže komunikovat prostřednictvím TCP i UDP podle zvolené varianty uživatelem. Byl vyvíjený v jazyce C.

## Prerekvizity

Program byl vyvíjený na Linux Ubuntu 20.00

- G++ na překlad zdrojového kódu
- Linux terminál - pro přeložení, spuštění a používání
- Server používající IPKCP(IPK Calculator Protocol)

## Spuštění a používání

V repozitáři se nachází makefile, který po zadání příkazu make. 

```
make
```

Poté už je klient připraven k používání. Spuštění se provede: 
`ipkcpc -h <host> -p <port> -m <mode>`
Přičemž host je IPV4 adresa serveru, mode je varianta protokolu UDP/TCP a port je port serveru.

## Průbeh programu po spuštění

Po spuštění programu následuje kontrola argumentů, tuto kontrolu zajišťuje funkce getopt(), a při špatně zadaných argumentech vypíše syntax používání programu.

Následně je pomocí funkce gethostbyname zjískána adresa serveru pomocí DNS, následně se nalezne adresa serveru a inicalizuje se struktura server_address.

Pokud program uspěje vypíše se informace o vzdáleném socketu a vztvoří se socket pro uživatele programu.

Následně se postupuje podle zvoleného protocolu uživatelem UDP/TCP.

## UDP
 
Komunikaci zajištuje cyklus while.
Uživatel je v této fázi vyzván k napsání zprávy kterou chce odeslat serveru, zpráva je zpracována funkcí fgets(), která vezme zprávu uživatele a vloží ji do pole s názvem "buf", poté je ověřeno jestli zpráva nepřevyšuje velikost pole, poté je zjištěna délka vtupního řetězce a ta je uložena do proměnné lenght_of_input_string.

Nyní proběhne inicializace pole "tmp_buf" do kterého se nahrají hexadecimální hodnoty, tento formát je vyžadován pro komunikaci.

Následně se vloží do prvních somi bitů tmp_buf operační kód 1, který značí, že zpráva je typu request, a do druhých osmi bitů se vloží délka odeslaného řetězce.

Poté se přesune obsah buf do tmp_buf, a proběhne odeslání zprávy serveru pomocí funkce sendto(). Poté po přijetí zpávy serverem, ktré zajištuje funkce recvfrom(), se zpráva nahraje do tmp_buf.

Poté je přečten ze zprávy operační kód 1 nebo 0. V případě 0 proběhlo vše v pořádku a je vypsána odpověd server. V případě 1 je vypsána chybová hláška.

Pokud vše proběhne v pořádku vrací se program na začátek cyklu a komunikace se opakuje.

Komunikace se ukončuje klávesovou zkratkou CTRL+C, tuto skutečnost zajištuje v programu funkce signal(), která klávesovou zkratku zachytí a následně je ukončeno spojení se serverem funkcí close() a program je ukon4


## TCP

Komunikaci opět zajištujě cyklus while












