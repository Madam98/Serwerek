Przydatne komendy - ściąga
Sprzęt w laboratorium
Komputery są wyposażone w 3 interfejsy sieciowe:

em1 (w mostku br0) - na górze, płynie nim Internet,

p4p1 - na dole po prawej patrząc od tyłu,

p4p2 - na dole po lewej patrząc od tyłu.

Żeby zidentyfikować interfejs sieciowy można użyć komendy ethtool, np. ethtool -p p4p1, co spowoduje, że dioda na interfejsie p4p1 zacznie mrugać.

Za komputerami znajdują się ponumerowane gniazdka sieciowe, które zazwyczaj są używane jak poniżej (patrząc od najniższych numerów do najwyższych):

gniazdko 1: połączenie z interfejsem p4p1,

gniazdko 2: puste,

gniazdko 3: płaski kabel niebieski, połączenie z portem szeregowym komputera (w Linuksie identyfikowany jako /dev/ttyS0), używane do łącznia się z konsolą Cisco,

gniazdko 4: połączenie z interfejsem em1.

Gniazdka za komputerami wyprowadzone są na patch panelach na zapleczu. Patch panele są ustawione od góry w takiej kolejności, by odpowiadać gniazdkom za komputerami.

Ponad patch panelami są switche (przełączniki) i routery. Żeby zresetować konfiguracje switcha czy routera, należy go zrestartować (przełącznikiem w przypadku routera, a poprzez wyciągnięcie kabla z prądem w przypadku switcha).

Urządzenia sieciowe łączy się kablami, które można znaleźć na wieszaku. Kable są dwojakiego rodzaju:

kable proste - czerwone, szare, niebieskie - mają identyczne końcówki, służą do łączenia urządzeń sąsiednich warstw, np. komputera ze switchem, switcha z routerem,

kable krosowane - czarne - mają różne końcówki, służą do łączenia urządzeń tej samej warstwy, np. switch ze switchem, router z routerem; powinny być także stosowane do łączenia komputera bezpośrednio z routerem.

Gdy komputery łączy się bezpośrednio powinno się to robić przy pomocy kabli krosowanych, bo łączone są urządzenia tej samej warstwy. Można jednak także korzystać z kabli prostych, bo wszystkie karty sieciowe w komputerach mają wsparcie dla Auto MDI-X, dzięki czemu potrafią wykryć jakim kablem są połączone z portem w drugim urządzeniem sieciowym i automatycznie zrekonfigurować swój port jeśli to jest potrzebne. Niektóre switche i routery na zapleczu też mają Auto MDI-X, ale nie wszystkie, więc lepiej łączyć je używać właściwych kabli.

Urządzenia Cisco konfiguruje się przez port konsolowy (niebieski, oznaczony jako Console, często znajduje się z tyłu urządzenia). Trzeba połączyć ten port z portem szeregowym w komputerze, który ma działać jako ekran i klawiatura dla tego urządzenia Cisco. W tym celu na zapleczu trzeba połączyć kablem prostym (najlepiej niebieskim, bo najdłuższym) port konsolowy z portem na patch panelu, który odpowiada gniazdku za komputerem, do którego podłączony jest niebieski płaski kabel wyprowadzony z portu szeregowego. Wtedy można użyć komendy np. picocom /dev/ttyS0 (jako root) by spróbować się skomunikować z urządzeniem Cisco. Gdy po naciśnięciu Enter nic się nie pojawia, trzeba sprawdzić:

czy podłączenie jest na właściwych gniazdkach,

czy kabel działa.

Z picocom wychodzi się ctrl-a-q.

Komendy
Podstawowe komendy (dokładny opis w Linuksie – patrz man <komenda>):

konfiguracja karty sieciowej:

ifconfig [eth0]

ifconfig eth0 up/down

ifconfig eth0 hw ether aa:bb:cc:dd:ee:ff

ethtool eth0

ethtool -s eth0 speed 10 duplex half autoneg off

ethtool -P eth0

ip link [show] [eth0]

ip link set eth0 up/down

ip link set eth0 address aa:bb:cc:dd:ee:ff

badanie statusu komputera w sieci:

ping 192.168.1.101

ping -b 192.168.1.255

badanie szybkości komunikacji w sieci:

netserver -D

netperf -H 192.168.1.101

konfiguracja adresu sieciowego

ip addr [show] [eth0]

ip addr add/del 192.168.1.101/24 dev eth0 [label eth0:1]

ifconfig eth0 192.168.1.101 netmask 255.255.255.0

śledzenie drogi pakietu

traceroute [-T/-U/-I] www.cs.put.poznan.pl

tracepath www.cs.put.poznan.pl

mtr www.cs.put.poznan.pl

ARP

ip neigh [show]

ip neigh add 192.168.1.101 lladdr aa:bb:cc:dd:ee:ff dev eth0

ip neigh del 192.168.1.101 dev eth0

ip link set arp on/off dev wlp3s0

arp

arp -i eth0 -s 192.168.1.101 aa:bb:cc:dd:ee:ff

arp -i eth0 -d 192.168.1.101

arping -I eth0 192.168.1.100

konfiguracja routingu

ip route [show]

ip route add 172.16.0.0/16 via 192.168.1.111

ip route del 172.16.0.0/16

ip route add default via 192.168.1.1

route [-n]

route add -net 172.16.0.0 netmask 255.255.0.0 gw 192.168.1.111

route del -net 172.16.0.0 netmask 255.255.0.0

route add default gw 192.168.1.1

konfiguracja przekazywania pakietów

cat /proc/sys/net/ipv4/ip_forward

echo 0/1 > /proc/sys/net/ipv4/ip_forward

sysctl net.ipv4.ip_forward

sysctl -w net.ipv4.ip_forward=0/1

połączenie z konsolą Cisco i podstawowe komendy

picocom /dev/ttyS0

konfiguracja interfejsów sieciowych w routerach Cisco

show interfaces

show ip interface brief (nie pokazuje adresów secondary!)

show interface FastEthernet 0/0

interface FastEthernet 0/0

ip address 192.168.1.1 255.255.255.0

no shutdown

ip address 172.16.13.13 255.255.128.0 secondary

ip address 10.10.10.10 255.255.240.0 secondary

interface Serial 0/1/0

ip address 10.0.0.1 255.255.0.0

clock rate 128000 (tylko na jednym routerze, końcówka DCE)

no shutdown

konfiguracja routingu w routerach Cisco

show ip route

ip route 172.16.0.0 255.255.0.0 192.168.1.111

ip route 0.0.0.0 0.0.0.0 192.168.1.1

router ospf 1

network 10.0.0.0 0.0.255.255 area 0 (uwaga, zanegowana maska!)

auto-cost reference-bandwidth 1000

show ip ospf neighbor

show ip route

show ip protocols

interface GigabitEthernet 0/1

bandwidth 25

ip ospf cost 17

ip route 0.0.0.0 0.0.0.0 192.168.51.17

default-information originate

konfiguracja VLANów na urządzeniach Cisco

show ip interface brief - które porty są aktywne

show vlan

interface FastEthernet 1/1

switchport access vlan 11

interface FastEthernet 1/19

switchport trunk encapsulation dot1q

switchport mode trunk

show interfaces trunk

interface GigabitEthernet 0/1 (na routerze)

no shutdown

interface GigabitEthernet 0/1.11

encapsulation dot1Q 11

ip address 192.168.1.101 255.255.255.0

interface GigabitEthernet 0/1.22

encapsulation dot1Q 22

ip address 10.10.20.20 255.255.0.0

listowanie połączeń:

netstat -tunap

netstat -tunap | grep ssh

operacje na gniazdach

ncat [-u] -l 192.168.1.55 1234 [> out.txt] oraz ncat [-u] 192.168.1.55 1234 [< in.txt]

ncat -l 192.168.1.55 1234 --chat oraz ncat 192.168.1.55 1234 --chat

ncat www.cs.put.poznan.pl 80 -> GET /tkobus HTTP/1.0 [ENTER][ENTER]

ncat -lk 192.168.1.55 1234 -c 'while true; do read i && echo [echo] $i; done'

filtrowanie pakietów

iptables -L

iptables -t filter|nat|mangle|raw -L -n -v -x --line-numbers

iptables -t filter -P INPUT|FORWARD|OUTPUT ACCEPT|DROP

iptables -F INPUT|FORWARD|OUTPUT

iptables -t nat -F PREROUTING|POSTROUTING

iptables -Z

iptables -A OUTPUT -p tcp --dport 80 -j ACCEPT

iptables -A INPUT -i wlan0 -s 192.168.55.0/24 -j REJECT

iptables -I INPUT -p tcp --help

iptables -A OUTPUT -m owner --gid-owner 1006 ! -d 192.168.1.0/24 -j DROP

iptables -A INPUT --protocol tcp --syn -j DROP (i równoważne iptables -A INPUT --protocol tcp --tcp-flags SYN,RST,ACK,FIN SYN -j DROP)

iptables -A INPUT -p tcp --syn --dport 23 -m connlimit --connlimit-above 2 -j REJECT

iptables -A INPUT -m mac ! --mac-source 00:12:34:56:78:ab -j DROP

iptables -A INPUT -p icmp --icmp-type echo-request -j ACCEPT

iptables -t nat -F

iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE

iptables -t nat -A POSTROUTING -j SNAT --to-source 150.254.130.41

iptables -t nat -A POSTROUTING -s 192.168.1.0/24 -d 10.0.0.0/8 -j SNAT --to-source 10.0.0.1

iptables -t nat -A PREROUTING -i eth0 -p tcp --dport 80 -j DNAT --to-destination 10.0.0.2

iptables -t nat -A PREROUTING -i eth0 -p tcp --dport 22 -j DNAT --to-destination 10.0.0.2:8008

inne przydatne komendy:

wireshark

zypper install <nazwa pakietu>