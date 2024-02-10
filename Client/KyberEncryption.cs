using Org.BouncyCastle.Crypto;
using Org.BouncyCastle.Pqc.Crypto.Crystals.Kyber;
using Org.BouncyCastle.Security;

public class KyberEncryption
{
    public ISecretWithEncapsulation GenerateEncapsulation(byte[] espPublicKey)
    {
        var kyberParameter = KyberParameters.kyber768;
        var secureRandom = new SecureRandom();
        var clientKemGenerator = new KyberKemGenerator(secureRandom);

        return clientKemGenerator.GenerateEncapsulated(new KyberPublicKeyParameters(kyberParameter, espPublicKey));
    }
}
