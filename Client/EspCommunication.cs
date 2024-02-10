using System.Net.Sockets;

public class EspCommunication
{
    private readonly NetworkStream _stream;

    public EspCommunication(NetworkStream stream)
    {
        _stream = stream;
    }

    public byte[] ReceivePublicKey()
    {
        var lengthBytes = new byte[4];
        _stream.Read(lengthBytes, 0, 4);
        var keyLength = BitConverter.ToInt32(lengthBytes, 0);

        var data = new byte[keyLength];
        _stream.Read(data, 0, keyLength);

        return data;
    }

    public void SendEncryptedData(byte[] data)
    {
        byte[] lengthBytes = BitConverter.GetBytes(data.Length);
        _stream.Write(lengthBytes, 0, 4);
        _stream.Write(data, 0, data.Length);
    }

    public byte[] ReceiveEncryptedData()
    {
        var lengthBytes = new byte[4];
        _stream.Read(lengthBytes, 0, 4);
        var dataLength = BitConverter.ToInt32(lengthBytes, 0);

        var data = new byte[dataLength];
        _stream.Read(data, 0, dataLength);

        return data;
    }
}
