import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.security.InvalidKeyException;
import java.security.Key;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.SignatureException;
import java.security.cert.CertificateException;
import java.security.cert.CertificateExpiredException;
import java.security.cert.CertificateFactory;
import java.security.cert.CertificateNotYetValidException;
import java.security.cert.X509Certificate;
import java.util.Base64;
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.swing.text.DefaultStyledDocument.ElementSpec;

public class ClientCP1 {

	public static void main(String[] args) {

		String serverAddress = "localhost";

    	int port = 4321;
		
		int numBytes = 0;

		Socket clientSocket = null;

        DataOutputStream toServer = null;
        DataInputStream fromServer = null;

    	FileInputStream fileInputStream = null;
        BufferedInputStream bufferedFileInputStream = null;

		if (args.length == 0){
			System.out.println("No files received!");
			throw new NullPointerException();
		}

		System.out.println("Files to print are: ");

		// for (int i=0; i<args.length; i++){
		// 	System.out.println(">>> " + args[i]);
		// }

		long timeStarted = System.nanoTime();

		try {

			System.out.println("Establishing connection to server...");

			// Connect to server and get the input and output streams
			clientSocket = new Socket(serverAddress, port);
			toServer = new DataOutputStream(clientSocket.getOutputStream());
			fromServer = new DataInputStream(clientSocket.getInputStream());
			
			////////////////////////////////////// AP //////////////////////////////////////
			PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
			out.println("Hello SecStore, please prove your identity!");

			// generate a nonce and send to server
			byte[] nonce = AP.sendNonce(toServer);

			// get encrypted reply from server
			byte[] encryptedReply = AP.clientGetEncryptedReply(fromServer);

			// Get encrypted Nonce from server
			byte[] encryptedNonce = AP.getEncryptedNonce(fromServer);
			
			// decrypt Nonce to check
			byte[] decryptedNonce = AP.decryptNonce("../keys/server_public_key.der", encryptedNonce);
			
			// compare Nonce 
			boolean isClientTheSame = AP.checkNonce(nonce, decryptedNonce);
			System.out.println("Is client the same: " + isClientTheSame);

			// Request for signed cert
			System.out.println("Requesting for Signed Cert from Server...");
			out.println("Give me your certificate signed by CA");

			// Get signed cert from server
			X509Certificate serverCert = AP.getSignedCert(fromServer);

			// Get public key of CA cert first so that we can use this to verify server's cert
			PublicKey CApublickey = AP.getCAkey();

			// Validate and verify server's public key
			PublicKey serverPublicKey = AP.validateAndVerify(serverCert, CApublickey);
			if (serverPublicKey != null){
				System.out.println("Extracted server's public key successfully");
			}
			
			// decrypt reply to check if it is secStore
			byte[] decryptedReply = AP.decryptMsg(serverPublicKey, encryptedReply);
			String strDecryptedReply = new String(decryptedReply);
			if (strDecryptedReply.equals("Hello, this is SecStore!")){
				System.out.println("It is indeed SecStore!");
			}else{
				System.out.println("Bye!");
				AP.end(bufferedFileInputStream, fileInputStream);
			}

			///////////////////////////////////////////////////////////////////////////////

			String filename = args[0];
			System.out.printf("Sending file %s...\n", args[0]);

			// Send the filename
			toServer.writeInt(0);
			toServer.writeInt(filename.getBytes().length);
			toServer.write(filename.getBytes());
			toServer.flush();

			// Open the file
			fileInputStream = new FileInputStream(filename);
			bufferedFileInputStream = new BufferedInputStream(fileInputStream);

			byte [] fromFileBuffer = new byte[117];

			// Send the file
			for (boolean fileEnded = false; !fileEnded;) {
				numBytes = bufferedFileInputStream.read(fromFileBuffer);
				byte[] encryptedFile = CP1.encryptFile(fromFileBuffer, serverPublicKey, toServer);

				fileEnded = numBytes < 117;

				toServer.writeInt(1);
				toServer.writeInt(encryptedFile.length);
				toServer.write(encryptedFile);
				toServer.flush();
			}
			AP.end(bufferedFileInputStream, fileInputStream);
			System.out.println("Closing connection...");

		} catch (Exception e) {e.printStackTrace();}

		long timeTaken = System.nanoTime() - timeStarted;
		System.out.println("Program took: " + timeTaken/1000000.0 + "ms to run");
	}
}
