# Ethernet (IEEE 802.3) Frame Format:

<img src="https://media.geeksforgeeks.org/wp-content/uploads/IEEE-802.3-Ethernet-Frame-Format.png" width=640>

## Preamble:
- The preamble consists of 7 bytes (56 bits) of alternating 1s and 0s: `10101010`
- Indicates starting of the frame and allow sender and receiver to establish bit synchronization
- Preamble: `10101010 10101010 10101010 10101010 10101010 10101010 10101010`

### Start of frame delimiter (SFD):
This is a 1-Byte field that is always set to `10101011`. SFD indicates that upcoming bits are starting the frame, which is the destination address.

### Destination Address
This is a 6-Byte field that contains the MAC address of the machine for which data is destined.

### Source Address
This is a 6-Byte field that contains the MAC address of the source machine.

### Length
- Length is a 2-Byte field, which indicates the length of the entire Ethernet frame
- This 16-bit field can hold a length value between 0 to 65534
- Length cannot be larger than 1500 Bytes because of some own limitations of Ethernet

### Data
- This is the place where actual data is inserted, also known as Payload
- The maximum data present may be as long as 1500 Bytes
- In case data length is less than minimum length i.e. 46 bytes, then padding 0’s is added to meet the minimum possible length

### Cyclic Redundancy Check (CRC)
- CRC is 4 Byte field
- This field contains a 32-bits hash code of data, which is generated over the Destination Address, Source Address, Length, and Data field
- If the checksum computed by destination is not the same as sent checksum value, data received is corrupted

### VLAN Tagging
- The Ethernet frame can also include a VLAN (Virtual Local Area Network) tag, which is a 4-byte field inserted after the source address and before the EtherType field
- This tag allows network administrators to logically separate a physical network into multiple virtual networks, each with its own VLAN ID

### Jumbo Frames
- In general, jumbo frames are considered to have a frame size of 9000 bytes or larger
- Look for options related to MTU or frame size and set it to the desired jumbo frame size 

### VLAN Frame Format (4 bytes)
In order that a Layer 2 switch can identify frames of different VLANs, a VLAN tag field is inserted into the data link layer encapsulation

<img src="https://download.huawei.com/mdl/image/download?uuid=e293a66aa668456881268c0a73b3e0bf">

1. Access links: Transmit untagged frames
2. Trunk links: Transmit tagged frames

**VLAN tag fields:**
| Field   | Length  | Description                | Value    | Description                                                                                                                                               |
|---------|---------|----------------------------|----------|-----------------------------------------------------------------------------------------------------------------------------------------------------------|
| TPID    | 2 Bytes | Tag Protocol Identifier    | 0x8100   | The TPID value is 0x8100, which indicates that the frame is VLAN-tagged.                                                                                  |
| PRI     | 3 Bit   | Priority                   | 0 - 7    | A larger value indicates a higher priority. If congestion occurs, the switch sends packets with the highest priority first.                               |
| CFI     | 1 Bit   | Canonical Format Indicator | 0/1      | 0 - MAC addresses are encapsulated in standard format 1 - MAC addresses are encapsulated in a non-standard format The value of this field is 0 by default |
| VLAN ID | 12 Bit  | VLAN ID                    | 0 - 4095 | The values 0 and 4095 are reserved, and therefore available VLAN IDs are in the range from 1 to 4094.                                                     |

### QinQ Packet Encapsulation Format
However, because the 12-bit VLAN tag field defined in IEEE 802.1Q identifies a maximum of 4096 VLANs, the number of users that 802.1Q VLANs can identify and isolate on metro Ethernet networks (MANs) is insufficient. To address this issue, QinQ is developed to expand VLAN space beyond 4096 VLANs so that a larger number of users can be identified on MANs. QinQ is developed to expand VLAN space by adding an additional 802.1Q tag to an 802.1Q packet. This increases the number of VLANs to 4094 x 4094.

<img src="https://download.huawei.com/mdl/image/download?uuid=34a751ae8a474b66a4cd17039b6e6af3">

### TPID:
Different carriers may use different TPID values in outer VLAN tags of QinQ frames.

| **Value**            | **Protocol Type** |
|----------------------|-------------------|
| 0x0806               | ARP               |
| 0x8035               | RARP              |
| 0x0800               | IP                |
| 0x86DD               | IPv6              |
| 0x8863/0x8864        | PPPoE             |
| 0x8847/0x8848        | MPLS              |
| 0x8137               | IPX/SPX           |
| 0x8809               | LACP              |
| 0x888E               | 802.1x            |
| 0x88A7               | HGMP              |
| 0xFFFD/0xFFFE/0xFFFF | Reserved          |