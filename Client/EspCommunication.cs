using System.Net.Sockets;

public class EspCommunication
{
    private readonly NetworkStream _stream;

    public EspCommunication(NetworkStream stream)
    {
        _stream = stream;
    }

    public byte[] ReceiveData()
    {
        var lengthBytes = new byte[4];
        _stream.Read(lengthBytes, 0, 4);
        var keyLength = BitConverter.ToInt32(lengthBytes, 0);

        var data = new byte[keyLength];
        _stream.Read(data, 0, keyLength);

        return data;
    }

    public void SendData(byte[] data)
    {
        byte[] lengthBytes = BitConverter.GetBytes(data.Length);
        _stream.Write(lengthBytes, 0, 4);
        _stream.Write(data, 0, data.Length);
    }
}
