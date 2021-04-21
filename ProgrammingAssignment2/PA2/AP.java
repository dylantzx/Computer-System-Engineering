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


public class AP {

    public static byte[] sendNonce(DataOutputStream toServer){
		try{
			System.out.println("Sending Nonce to the server...");
			byte[] nonce = new byte[32]; 
			SecureRandom sr = SecureRandom.getInstance("SHA1PRNG");
			sr.nextBytes(nonce);

            // String base64formatedNonce = Base64.getEncoder().encodeToString(nonce);
			// System.out.println(">> " + base64formatedNonce);

			toServer.writeInt(nonce.length);
			toServer.write(nonce);
			toServer.flush();

			return nonce;
		}catch(Exception e){
			e.printStackTrace();
		}
		return null;
	}

    public static byte[] getNonce(DataInputStream fromClient){
		try{
			System.out.println("Receiving Nonce from Client...");
			int NonceBytesLength = fromClient.readInt();
			byte[] NonceBytes = new byte[NonceBytesLength];
			fromClient.readFully(NonceBytes, 0, NonceBytesLength);
			System.out.println("Received Nonce");

			// String base64formatedNonce = Base64.getEncoder().encodeToString(NonceBytes);
			// System.out.println(">> " + base64formatedNonce);

			return NonceBytes;
		}catch(IOException e){
			e.printStackTrace();
		}
		return null;
	}

    public static void sendEncryptedReply(DataOutputStream toClient){
		try{
			System.out.println("Sending encrypted reply to the client...");
			String reply = "Hello, this is SecStore!";
			PrivateKey privateKey = PrivateKeyReader.get("../keys/server_private_key.der");
			Cipher rsaCipher = Cipher.getInstance("RSA/ECB/PKCS1Padding");
			rsaCipher.init(Cipher.ENCRYPT_MODE, privateKey);
			byte[] encryptedBytes = rsaCipher.doFinal(reply.getBytes());
			toClient.writeInt(encryptedBytes.length);
			toClient.write(encryptedBytes);
			toClient.flush();
		 } catch(Exception e){
			 e.printStackTrace();
		 }
	}

    public static byte[] clientGetEncryptedReply(DataInputStream fromServer) {
		try{
			int encryptedReplyLength = fromServer.readInt();
			byte[] encryptedReplyBytes = new byte[encryptedReplyLength];
			fromServer.readFully(encryptedReplyBytes, 0, encryptedReplyLength);
			System.out.println("Received encrypted reply from server");
			return encryptedReplyBytes;

		}catch (IOException e){
			e.printStackTrace();
		}
		return null;
	}

    public static void sendEncryptedNonce(byte[] nonce, DataOutputStream toClient){
		System.out.println("Sending encrypted Nonce...");
		try {
			PrivateKey serverPrivateKey = PrivateKeyReader.get("../keys/server_private_key.der");
			Cipher rsaCipher = Cipher.getInstance("RSA/ECB/PKCS1Padding");
			rsaCipher.init(Cipher.ENCRYPT_MODE, serverPrivateKey);
			byte[] encryptedNonce = rsaCipher.doFinal(nonce);

			toClient.writeInt(encryptedNonce.length);
			toClient.write(encryptedNonce);
			toClient.flush();

			System.out.println("Successfully sent encrypted Nonce");
		} catch (Exception e1) {
			e1.printStackTrace();
		}
		
	}

    public static byte[] getEncryptedNonce(DataInputStream fromServer) {
		try{
			int encryptedNonceBytesLength = fromServer.readInt();
			byte[] encryptedNonceBytes = new byte[encryptedNonceBytesLength];
			fromServer.readFully(encryptedNonceBytes, 0, encryptedNonceBytesLength);
			System.out.println("Received encrypted nonce from server");
			return encryptedNonceBytes;
		}catch (IOException e){
			e.printStackTrace();
		}
		return null;
	}

    public static byte[] decryptNonce(String path, byte[] EncryptedNonce){
		try{
			PublicKey publicKey = PublicKeyReader.get(path);
			Cipher rsaCipherDecrypt = Cipher.getInstance("RSA/ECB/PKCS1Padding");
			rsaCipherDecrypt.init(Cipher.DECRYPT_MODE, publicKey);
			return rsaCipherDecrypt.doFinal(EncryptedNonce);

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

    public static byte[] decryptMsg(PublicKey serverPublicKey, byte[] EncryptedMsg){
		try{
			Cipher rsaCipherDecrypt = Cipher.getInstance("RSA/ECB/PKCS1Padding");
			rsaCipherDecrypt.init(Cipher.DECRYPT_MODE, serverPublicKey);
			return rsaCipherDecrypt.doFinal(EncryptedMsg);

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

	public static Boolean checkNonce(byte[] nonce, byte[] decryptedNonce){
		String base64formatedNonce = Base64.getEncoder().encodeToString(nonce);
		System.out.println(">> " + base64formatedNonce);
		String base64formatedDecryptedNonce = Base64.getEncoder().encodeToString(decryptedNonce);
		System.out.println(">> " + base64formatedDecryptedNonce);
		
		return base64formatedNonce.equals(base64formatedDecryptedNonce);
	}

	

	public static PublicKey getCAkey(){

		try{
			InputStream CAfis = new FileInputStream("../keys/cacsertificate.crt");
			CertificateFactory CAcf = CertificateFactory.getInstance("X.509");
			X509Certificate CACert = (X509Certificate)CAcf.generateCertificate(CAfis);
			return CACert.getPublicKey();
		}catch(FileNotFoundException e){
			e.printStackTrace();
		}catch(CertificateException e){
			e.printStackTrace();
		}
		return null;
	}

	public static X509Certificate getSignedCert(DataInputStream fromServer){

		try{
			int numBytes = fromServer.readInt();
			byte[] ServerCertBytes = new byte[numBytes];
			fromServer.readFully(ServerCertBytes, 0, numBytes);

			InputStream fis = new ByteArrayInputStream(ServerCertBytes);
			CertificateFactory cf = CertificateFactory.getInstance("X.509");
			X509Certificate serverCert = (X509Certificate)cf.generateCertificate(fis);
			System.out.println("Received signed certificate. Verifying Server Cert...");
			return serverCert;
		}catch(IOException e){
			e.printStackTrace();
		}catch(CertificateExpiredException e){
			e.printStackTrace();
		}catch(CertificateException e){
			e.printStackTrace();
		}
		return null;
	}

	public static PublicKey validateAndVerify(X509Certificate serverCert, PublicKey CAKey){
		
		try {
			serverCert.checkValidity();
			serverCert.verify(CAKey);
			System.out.println("Verified Server Cert!");
			return serverCert.getPublicKey();
		}catch (CertificateExpiredException e) {
			e.printStackTrace();
		}catch (CertificateException e) {
			e.printStackTrace();
		}catch (InvalidKeyException | NoSuchAlgorithmException | NoSuchProviderException | SignatureException e) {
			e.printStackTrace();
		}
		return null;
	}

	public static void sendSignedCert(DataOutputStream toClient){
		try{
			System.out.println("Sending signed certificate...");
			InputStream fis = new FileInputStream("../keys/serverCert.crt");
			CertificateFactory cf = CertificateFactory.getInstance("X.509");
			X509Certificate ServerCert = (X509Certificate)cf.generateCertificate(fis);
			byte[] ServerCertByte = ServerCert.getEncoded();
			toClient.writeInt(ServerCertByte.length);
			toClient.write(ServerCertByte);
			toClient.flush();
			System.out.println("Sent signed certificate. Now waiting for Client to verify...");
		}catch(Exception e){
			e.printStackTrace();
		}
		
	}

	public static void end(BufferedInputStream bufferedFileInputStream,FileInputStream fileInputStream ){
		try{
			bufferedFileInputStream.close();
	        fileInputStream.close();
		}catch(IOException e){
			e.printStackTrace();
		}
		
	}
}
