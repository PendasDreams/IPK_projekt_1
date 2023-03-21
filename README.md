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











