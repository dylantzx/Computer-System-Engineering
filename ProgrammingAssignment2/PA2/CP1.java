import java.io.BufferedOutputStream;
import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;

import java.io.ByteArrayInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

import java.net.ServerSocket;
import java.net.Socket;

import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.SecureRandom;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;
import java.security.InvalidKeyException;
import java.security.Key;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.SignatureException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.cert.CertificateException;
import java.security.cert.CertificateExpiredException;
import java.security.cert.CertificateFactory;
import java.security.cert.CertificateNotYetValidException;

import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;

import java.util.Base64;

public class CP1 {
    public static byte[] encryptFile(byte[] file, PublicKey serverKey, DataOutputStream toServer){
        try{
			System.out.println("Sending encrypted file to the server...");
			Cipher rsaCipher = Cipher.getInstance("RSA/ECB/PKCS1Padding");
			rsaCipher.init(Cipher.ENCRYPT_MODE, serverKey);
			byte[] encryptedBytes = rsaCipher.doFinal(file);
			return encryptedBytes;

		 } catch(Exception e){
			 e.printStackTrace();
		 }
		 return null;
    }

    public static byte[] decryptFile(byte[] EncryptedFile){
		try{
            PrivateKey privateKey = PrivateKeyReader.get("../keys/server_private_key.der");
			Cipher rsaCipherDecrypt = Cipher.getInstance("RSA/ECB/PKCS1Padding");
			rsaCipherDecrypt.init(Cipher.DECRYPT_MODE, privateKey);
			return rsaCipherDecrypt.doFinal(EncryptedFile);

		}catch(IllegalBlockSizeException e){
			e.printStackTrace();
		}catch(InvalidKeyException e){
			e.printStackTrace();
		}catch(NoSuchAlgorithmException e){
			e.printStackTrace();
		}catch(Exception e){
			e.printStackTrace();
		}
		return null;
	}
}
