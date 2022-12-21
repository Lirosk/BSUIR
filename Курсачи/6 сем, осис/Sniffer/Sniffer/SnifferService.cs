using PacketDotNet;
using SharpPcap;
using System;
using System.Data;
using System.IO;
using System.Linq;
using System.ServiceProcess;

namespace Sniffer
{
    public partial class SnifferService : ServiceBase
    {
        private string file;

        private StreamWriter writer;

        private CaptureDeviceList devices;

        public SnifferService()
        {
            InitializeComponent();

            this.file = Path.Combine(
            Environment.GetFolderPath(
                Environment.SpecialFolder.Desktop),
                "captured.txt");

            this.writer = new StreamWriter(
                File.OpenWrite(file));

            this.devices = CaptureDeviceList.Instance;
        }

        protected override void OnStart(string[] args)
        {
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

            var packet = Packet.ParsePacket(e_packet.LinkLayerType, e_packet.Data);

            IPPacket ipPacket = packet.Extract<IPPacket>();

            if (ipPacket != null)
            {
                System.Net.IPAddress srcIp = ipPacket.SourceAddress;
                System.Net.IPAddress dstIp = ipPacket.DestinationAddress;
                var protocol_type = ipPacket.Protocol;
                var sourceIP = srcIp.ToString();
                var destinationIP = dstIp.ToString();
                var payload_packet = ipPacket.PayloadPacket;
                var ttl = ipPacket.TimeToLive;

                WritePacket(packet, protocol_type, sourceIP, destinationIP, payload_packet, time_str, ttl);
                Console.WriteLine("\n");
            }
        }

        private void WritePacket(
            Packet packet, ProtocolType protocol,
            string sourceIP, string destinationIP,
            Packet payload_packet, string time, int ttl)
        {
            this.writer.WriteLine($"Time: {time}");
            this.writer.WriteLine($"Protocol type: {protocol.ToString()}");
            this.writer.WriteLine($"Source ip: {sourceIP}");
            this.writer.WriteLine($"Destination ip: {destinationIP}");
            this.writer.WriteLine($"Time to live: {ttl}");


            switch (protocol)
            {
                case ProtocolType.Tcp:
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
                                "\r\nData offset: " + tcpPacket.DataOffset +
                                "\r\nWindow size: " + tcpPacket.WindowSize +
                                "\r\nChecksum:" + checksum.ToString() + (tcpPacket.ValidChecksum ? ",valid" : ",invalid") +
                                "\r\nTCP checksum: " + (tcpPacket.ValidTcpChecksum ? ",valid" : ",invalid") +
                                "\r\nSequence number: " + tcpPacket.SequenceNumber.ToString() +
                                "\r\nAcknowledgment number: " + tcpPacket.AcknowledgmentNumber + (tcpPacket.Acknowledgment ? ",valid" : ",invalid") +
                                "\r\nUrgent pointer: " + (tcpPacket.Urgent ? "valid" : "invalid") +
                                "\r\nACK flag: " + (tcpPacket.Acknowledgment ? "1" : "0") +
                                "\r\nPSH flag: " + (tcpPacket.Push ? "1" : "0") +
                                "\r\nRST flag: " + (tcpPacket.Reset ? "1" : "0") +
                                "\r\nSYN flag: " + (tcpPacket.Synchronize ? "1" : "0") +
                                "\r\nFIN flag: " + (tcpPacket.Finished ? "1" : "0") +
                                "\r\nNS flag: " + (tcpPacket.NonceSum ? "1" : "0") +
                                "\r\nCWR flag: " + (tcpPacket.CongestionWindowReduced ? "1" : "0") +
                                "\r\nECE flag: " + (tcpPacket.ExplicitCongestionNotificationEcho ? "1" : "0") +
                                "\r\nURG flag: " + (tcpPacket.Urgent ? "1" : "0") +
                                $"\r\nPayload data: {string.Join("", payload_packet.PayloadData.Select((o) => o.ToString("x")))}";

                            writer.WriteLine(str);
                            writer.WriteLine("\n");
                            Console.WriteLine(str);
                        }
                        break;
                    }
                case ProtocolType.Udp:
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
            }

            writer.Flush();
        }
    }
}
