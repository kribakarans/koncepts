# OSI model

| **TCP/IP Model** | **OSI Model** | **Data Unit**     | **Devices**                 | **Protocols**                                           | **Operations**                                            |
|------------------|---------------|-------------------|-----------------------------|---------------------------------------------------------|-----------------------------------------------------------|
| Application      | Application   |        Data       |                             | SMTP, HTTP, FTP, POP3, SNMP, Telnet                     |                                                           |
|         "        | Presentation  |         "         |                             | SSL, TLS                                                | Translate, encrypt and compress dat                       |
|         "        | Session       |         "         | Gateway                     | Sockets(TCP, RTP)                                       | Establish, manage, and terminate the session              |
| Transport        | Transport     | Segment, Datagram | Firewall                    | TCP, UDP                                                |                                                           |
| Network          | Network       |       Packet      | Router                      | IPV4, IPV6, ICMP, IPSEC, ARP, MPLS                      | Move packets from source to destination                   |
| Datalink         | Datalink      |       Frame       | Switch, Bridge              | PPP, Frame Relay, ATM, IEEE 802.3, NDP, LLDP, STP, VLAN | Organize bits into frames. To provide hop-to-hop delivery |
| Physical         | Physical      |        Bit        | Hub, Repeater, Modem, Cable | RS232, 100BaseTX, ISDN, RJ45, Token Rings               | Transmit bits over a medium                               |
