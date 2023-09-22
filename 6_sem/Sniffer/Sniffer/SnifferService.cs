using PacketDotNet;
using SharpPcap;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.ServiceProcess;
using System.Text;
using System.Threading.Tasks;

namespace Sniffer
{
    public partial class SnifferService : ServiceBase
    {
        static private string file = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "captured.txt");
        private StreamWriter writer = new StreamWriter(File.OpenWrite(file));
        CaptureDeviceList devices = CaptureDeviceList.Instance;

        public SnifferService()
        {
            InitializeComponent();
        }

        protected override void OnStart(string[] args)
        {
            Console.WriteLine(Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), "capture.pcap"));

            foreach (var device in devices)
            {
                device.Open();
                device.OnPacketArrival += Device_OnPacketArrival;
                device.StartCapture();
            }
        }

        protected override void OnStop()
        {
            foreach (var device in this.devices)
            {
                device.Close();
            }

            writer.Close();
        }

        private void Device_OnPacketArrival(object s, PacketCapture e)
        {
            var e_packet = e.GetPacket();

            DateTime time = e_packet.Timeval.Date;
            var time_str = (time.Hour + 1) + ":" + time.Minute + ":" + time.Second + ":" + time.Millisecond;

            var packet = PacketDotNet.Packet.ParsePacket(e_packet.LinkLayerType, e_packet.Data);

            IPPacket ipPacket = packet.Extract<IPPacket>();

            if (ipPacket != null)
            {
                System.Net.IPAddress srcIp = ipPacket.SourceAddress;
                System.Net.IPAddress dstIp = ipPacket.DestinationAddress;
                var protocol_type = ipPacket.Protocol.ToString();
                var sourceIP = srcIp.ToString();
                var destinationIP = dstIp.ToString();
                var payload_packet = ipPacket.PayloadPacket;

                WritePacket(packet, protocol_type, sourceIP, destinationIP, payload_packet, time_str);
                Console.WriteLine("\n");
            }
        }

        private void WritePacket(Packet packet, string protocol, string sourceIP, string destinationIP, Packet payload_packet, string time)
        {
            protocol = protocol.ToUpperInvariant();

            Console.WriteLine($"Time: {time}");
            Console.WriteLine($"Protocol type: {protocol}");
            Console.WriteLine($"Source ip: {sourceIP}");
            Console.WriteLine($"Destination ip: {destinationIP}");

            this.writer.WriteLine($"Time: {time}");
            this.writer.WriteLine($"Protocol type: {protocol}");
            this.writer.WriteLine($"Source ip: {sourceIP}");
            this.writer.WriteLine($"Destination ip: {destinationIP}");


            switch (protocol)
            {
                case "TCP":
                    {
                        var tcpPacket = packet.Extract<TcpPacket>();
                        if (tcpPacket != null)
                        {
                            int srcPort = tcpPacket.SourcePort;
                            int dstPort = tcpPacket.DestinationPort;
                            var checksum = tcpPacket.Checksum;

                            var str =
                                "Source port:" + srcPort +
                                "\r\nDestination port: " + dstPort +
                                "\r\nTCP header size: " + tcpPacket.DataOffset +
                                "\r\nWindow size: " + tcpPacket.WindowSize + // bytes that the receiver is willing to receive
                                "\r\nChecksum:" + checksum.ToString() + (tcpPacket.ValidChecksum ? ",valid" : ",invalid") +
                                "\r\nTCP checksum: " + (tcpPacket.ValidTcpChecksum ? ",valid" : ",invalid") +
                                "\r\nSequence number: " + tcpPacket.SequenceNumber.ToString() +
                                "\r\nAcknowledgment number: " + tcpPacket.AcknowledgmentNumber + (tcpPacket.Acknowledgment ? ",valid" : ",invalid") +
                                // flags
                                "\r\nUrgent pointer: " + (tcpPacket.Urgent ? "valid" : "invalid") +
                                "\r\nACK flag: " + (tcpPacket.Acknowledgment ? "1" : "0") + // indicates if the AcknowledgmentNumber is valid
                                "\r\nPSH flag: " + (tcpPacket.Push ? "1" : "0") + // push 1 = the receiver should pass the data to the app immidiatly, don't buffer it
                                "\r\nRST flag: " + (tcpPacket.Reset ? "1" : "0") + // reset 1 is to abort existing connection
                                                                                   // SYN indicates the sequence numbers should be synchronized between the sender and receiver to initiate a connection
                                "\r\nSYN flag: " + (tcpPacket.Synchronize ? "1" : "0") +
                                // closing the connection with a deal, host_A sends FIN to host_B, B responds with ACK
                                // FIN flag indicates the sender is finished sending
                                "\r\nFIN flag: " + (tcpPacket.Finished ? "1" : "0") +
                                "\r\nECN flag: " + (tcpPacket.ExplicitCongestionNotificationEcho ? "1" : "0") +
                                "\r\nCWR flag: " + (tcpPacket.CongestionWindowReduced ? "1" : "0") +
                                "\r\nNS flag: " + (tcpPacket.NonceSum ? "1" : "0") +
                                $"\r\nPayload data: {string.Join("", payload_packet.PayloadData.Select((o) => o.ToString("x")))}";

                            writer.WriteLine(str);
                            writer.WriteLine("\n");
                            Console.WriteLine(str);
                        }
                        break;
                    }
                case "UDP":
                    {
                        var udpPacket = packet.Extract<UdpPacket>();
                        if (udpPacket != null)
                        {
                            int srcPort = udpPacket.SourcePort;
                            int dstPort = udpPacket.DestinationPort;
                            var checksum = udpPacket.Checksum;

                            var str =
                                "Source port:" + srcPort +
                                "\r\nDestination port: " + dstPort +
                                "\r\nChecksum:" + checksum.ToString() + " valid: " + udpPacket.ValidChecksum +
                                "\r\nValid UDP checksum: " + udpPacket.ValidUdpChecksum +
                                $"\r\nPayload data: {string.Join("", payload_packet.PayloadData.Select((o) => o.ToString("x")))}";

                            writer.WriteLine(str);
                            writer.WriteLine("\n");
                            Console.WriteLine(str);
                        }
                        break;
                    }
                case "ARP":
                    {
                        var arpPacket = packet.Extract<ArpPacket>();
                        if (arpPacket != null)
                        {
                            System.Net.IPAddress senderAddress = arpPacket.SenderProtocolAddress;
                            System.Net.IPAddress targerAddress = arpPacket.TargetProtocolAddress;
                            System.Net.NetworkInformation.PhysicalAddress senderHardwareAddress = arpPacket.SenderHardwareAddress;
                            System.Net.NetworkInformation.PhysicalAddress targerHardwareAddress = arpPacket.TargetHardwareAddress;

                            var str =
                                "Hardware address length:" + arpPacket.HardwareAddressLength +
                                "\r\nProtocol address length: " + arpPacket.ProtocolAddressLength +
                                "\r\nOperation: " + arpPacket.Operation.ToString() + // ARP request or ARP reply ARP_OP_REQ_CODE, ARP_OP_REP_CODE
                                "\r\nSender protocol address: " + senderAddress +
                                "\r\nTarget protocol address: " + targerAddress +
                                "\r\nSender hardware address: " + senderHardwareAddress +
                                "\r\nTarget hardware address: " + targerHardwareAddress;

                            writer.WriteLine(str);
                            writer.WriteLine("\n");
                            Console.WriteLine(str);
                        }
                    }
                    break;
                case "ICMP":
                    {
                        var icmpPacket = packet.Extract<IcmpV4Packet>();
                        if (icmpPacket != null)
                        {
                            var str =
                                "Type Code: 0x" + icmpPacket.TypeCode.ToString("x") +
                                "\r\nChecksum: " + icmpPacket.Checksum.ToString("x") +
                                "\r\nID: 0x" + icmpPacket.Id.ToString("x") +
                                "\r\nSequence number: " + icmpPacket.Sequence.ToString("x");

                            writer.WriteLine(str);
                            writer.WriteLine("\n");
                            Console.WriteLine(str);
                        }
                    }
                    break;
                case "IGMP":
                    {
                        var igmpPacket = packet.Extract<IgmpV2Packet>();
                        if (igmpPacket != null)
                        {
                            var str =
                                "Type: " + igmpPacket.Type +
                                "\r\nGroup address: " + igmpPacket.GroupAddress +
                                "\r\nMax response time" + igmpPacket.MaxResponseTime;

                            writer.WriteLine(str);
                            writer.WriteLine("\n");
                            Console.WriteLine(str);
                        }
                    }
                    break;
            }

            writer.Flush();
        }
    }
}
