package com.snhu.sslserver;

import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class SslServerApplication {

	public static void main(String[] args) {
		SpringApplication.run(SslServerApplication.class, args);
	}

}

@RestController
class ServerController {

	@GetMapping("/hash")
	public String myHash() {
		String data = "Uri Naor - Artemis Financial checksum 2026-10-17";
		String algo = "SHA-256";

		try {
			MessageDigest msg = MessageDigest.getInstance(algo);
			byte[] hash = msg.digest(data.getBytes(StandardCharsets.UTF_8));
			String checksum = bytesToHex(hash);

			String res = "<p>Data: " + data + "</p>"
					+ "<p>Algorithm: " + algo + "</p>"
					+ "<p>CheckSum: " + checksum + "</p>";
			return res;
		} catch (Exception e) {
			return "<p>Error: the checksum could not be generated.</p>";
		}
	}

	private static String bytesToHex(byte[] bytes) {
		StringBuilder hexa = new StringBuilder();
		for (byte byt : bytes) {
			hexa.append(String.format("%02x", byt));
		}
		return hexa.toString();
	}
}
