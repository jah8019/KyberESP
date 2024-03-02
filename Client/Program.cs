using System.Net.Sockets;
using System.Text;

class Program
{
    private const string IpAddress = "192.168.178.149"; // Replace this with the IP address of your Arduino board
    private const int Port = 80; // Use the same port in the C++ code
    private static readonly byte[] InitVector = { 32, 19, 42, 33, 14, 61, 12, 91, 40, 74, 32, 17, 31, 78, 18, 0 };

    static void Main()
    {
        var client = new TcpClient();
        client.Connect(IpAddress, Port);

        var stream = client.GetStream();

        var espCommunication = new EspCommunication(stream);
        var espPublicKey = espCommunication.ReceiveData();
        Console.WriteLine($"Received espPublicKey: {PrettyPrint(espPublicKey)}");

        var kyberEncryption = new KyberEncryption();
        var encapsulatedSecret = kyberEncryption.GenerateEncapsulation(espPublicKey);
        var cypherText = encapsulatedSecret.GetEncapsulation();
        Console.WriteLine($"Printing encapsulatedSecret: {PrettyPrint(cypherText)}");
        var sharedSecret = encapsulatedSecret.GetSecret();
        Console.WriteLine($"Secret: {PrettyPrint(sharedSecret)}");

        espCommunication.SendData(cypherText);

        var plaintext = "This is an encrypted text";
        var aesEncryption = new AesEncryption();
        var encryptedText = aesEncryption.Encrypt(plaintext, sharedSecret, InitVector);
        Console.WriteLine($"Sending: {plaintext} as: {PrettyPrint(encryptedText)}");
        espCommunication.SendData(encryptedText);

        stream.Close();
        client.Close();
    }

    static string PrettyPrint(byte[] bytes)
    {
        Console.WriteLine($"Length: {bytes.Length}");
        var stringBuilder = new StringBuilder();
        foreach (var b in bytes)
        {
            stringBuilder.AppendFormat("{0:x}", b);
        }
        return stringBuilder.ToString();
    }
}
