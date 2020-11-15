#ARP-control-server // PNRPU (c) cyberlab
from scapy.all import srp, Ether, ARP, sniff, wrpcap, PcapReader
import sqlite3, time
global arp_table
arp_table = dict()
#method to scan network configuration and create IP-MAC-HOST table
def arp_scan(network):
    assert isinstance(network, str), 'example 192.168.0.0/24'
    ans, unans = srp(Ether(dst="ff:ff:ff:ff:ff:ff")/ARP(pdst=network),timeout=2)
    for pkt in ans:
        IP = pkt[1].psrc
        MAC = pkt[1].src 
        if IP not in arp_table.keys():
            arp_table[IP] =  MAC  

    
#method for sniffing network and log arp
def arp_filter():
    sniff(filter='arp', prn=arp_handler)

def arp_handler(pkt):
    IP = pkt.psrc
    MAC = pkt.src
    event_time = time.strftime("%d-%m-%Y %H.%M.%S", time.localtime())
    if IP not in arp_table.keys():
            arp_table[IP] =  MAC
            return f'{event_time} new host detected {IP} - {MAC} added to arp_table'
    if IP in arp_table.keys() and MAC != arp_table.get(IP):
        try:
            host = select_host_from_db(MAC)
            if str(host) == 'None':
               host = IP
        except BaseException:
            host = IP
        
        wrpcap(f'/home/cyberlab/pydata/{time.localtime().tm_mday}_arp_alert.pcap',pkt, append = True)
        log = open('/home/cyberlab/pydata/arp.log', 'a')
        log.write(f'{event_time} {host} alert ARP-spoofing detected from {MAC}')        
        return f'{event_time} {host} alert ARP-spoofing detected from {MAC}'

#method for log analysis with ARP_DB
def add_host_to_table():
    for IP in arp_table:
        MAC = arp_table.get(IP)       
        hostname = select_host_from_db()
        arp_table[IP].append(hostname)
        
#DB / file methods
def initialize_local_db():
    conn = sqlite3.connect("/home/cyberlab/pydata/security.db") 
    cursor = conn.cursor()
    cursor.execute("""CREATE TABLE IF NOT EXISTS hosts
                  (basic_net TEXT, mac TEXT,
                   hostname TEXT)
               """)
    conn.commit()

def insert_host_in_db(net,MAC,hostname):
    conn = sqlite3.connect("/home/cyberlab/pydata/security.db")
    cursor = conn.cursor()
    cmd = f"INSERT INTO hosts (basic_net, MAC, hostname) VALUES ('{str(net)}', '{str(MAC)}', '{str(hostname)}');"
    cursor.execute(cmd)
    conn.commit()

def select_host_from_db(MAC):
    db = sqlite3.connect('/home/cyberlab/pydata/security.db')
    db.row_factory = lambda cursor, row: row[0]
    cur = db.cursor()
    db_req = f'SELECT hostname FROM hosts WHERE mac="{MAC}";'    
    cur.execute(db_req)
    hostname = cur.fetchone()
    return hostname

# Создание таблицы

   
    
#method to get MAC for HOST from DB

#alert methods


#programm example
arp_scan('192.168.0.0/24')
arp_filter()
#initialize_local_db()
#insert_host_in_db('local','FF:FF:FF:FF:FF:FF', 'broadcast')
#select_host_from_db('FF:FF:FF:FF:FF:FF')
#
