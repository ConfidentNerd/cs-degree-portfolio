# Software Security (CS 305)

A Java Spring Boot web app refactored for Artemis Financial to use HTTPS and SHA-256 checksum verification.

**Artifact:** [Artemis Financial - Practices for Secure Software Report](CS%20305%20Project%20Two%20-%20Uri%20Naor.docx) (Project Two)

---

## Project Reflection

**Briefly summarize your client, Artemis Financial, and its software requirements. Who was the client? What issue did the company want you to address?**

Artemis Financial is a consulting company that develops individualized financial plans for its customers. Specifically plans like savings, retirement, investments, and insurance. In other words, they handle very sensitive personal information. In essence, they are in the business of earning their customer's trust.

Luckily it seems to me that the company understands this, as they're actively pursuing to improve and modernize their security, which is why we were hired. Specifically, they wanted us to find the security vulnerabilities in their web application and then add secure communications to it, including HTTPS and a checksum to verify that data isn't changed when it's transferred.

**What did you do well when you found your client's software security vulnerabilities? Why is it important to code securely? What value does software security add to a company's overall well-being?**

I think what I did well was going through the code manually, one issue at a time, instead of relying only on the tools. That's how I caught things like credentials written right into the code, a stack trace printed instead of handling the error, a deposit() method that doesn't check for negative amounts, and a dependency in the pom.xml file that likely isn't even being used.

My biggest takeaway from this course is that software vulnerabilities arise from developer decisions and honest human oversight. Developers make decisions throughout the entire life cycle of an application and you honestly don't need to look for some complicated or sophisticated hacking technique to explain why vulnerabilities exist. Many vulnerabilities result simply from ordinary choices people make in their everyday work.

Security is always valuable to any company, but especially in the case of Artemis. Security has a major and direct impact on their business. For example, if any personal or financial details of their customers leak, or worse, get modified in any way, this could have a major impact on both the customer and the reputation of the company, and possibly even get the attention of media companies and the news. On top of that, Artemis has to follow the Gramm-Leach-Bliley Act (GLBA), so securing the data isn't a nice-to-have, it's a must.

**Which part of the vulnerability assessment was challenging or helpful to you?**

The dependency check was both the most helpful and the most challenging part for me. At first the report looked overwhelming, with hundreds of vulnerabilities, but looking at the list of vulnerable dependencies I could see that almost all of them were inherited from spring-boot-starter-parent 2.2.4.RELEASE, so simply updating it would clear most of them.

Another challenge was false positives. The tool has to guess which library each jar is, and sometimes it matches the wrong one and reports vulnerabilities that don't really apply. If we don't filter those then the report looks slightly worse than reality, and we can waste time looking into things that turn out to be nothing, or even might start ignoring the report altogether and miss a real vulnerability.

**How did you increase layers of security? In the future, what would you use to assess vulnerabilities and decide which mitigation techniques to use?**

As for my process for adding layers of security, I view it as a step-by-step process of building them one on top of the other, so that if one layer fails, the others still protect the data. For example, in this case, the HTTPS encrypts the data, so a person sitting in the middle of the connection won't be able to read it. Then for another layer the SHA-256 checksum lets Artemis verify that the data wasn't changed. Other security measures include that errors are handled without leaking internal details and I made sure vulnerabilities in general are minimized by running the dependency check and manually reviewing the code to make sure that the refactoring didn't add any new security issues.

In the future I'd start with the vulnerability assessment process flow diagram, going through its seven areas of security to decide which ones apply and which parts of the code need a manual review. When deciding what to fix first, I wouldn't just go by how many CVEs each dependency has. The dependency-check report marks a few of them with an asterisk to indicate the dependency has a known exploited vulnerability, meaning they've been used in real attacks, so I'd start with those and then work down by severity (Critical -> High -> Medium and so on). I'd also make these checks automatic. For example we could add static security testing directly into the development environment so that the code is checked while it is being written. Or adding automated scanning to catch vulnerabilities before releases go live and so on.

**How did you make certain the code and software application were functional and secure? After refactoring the code, how did you check to see whether you introduced new vulnerabilities?**

I didn't find any syntax errors, and the refactored code compiles and runs with no errors. I also opened https://localhost:8443/hash in the browser to check that the checksum works over HTTPS, and used the browser's certificate viewer to confirm the server is using the certificate I generated.

After refactoring, I ran the OWASP dependency-check tool on the refactored code. The only code I added uses Java's built-in MessageDigest class, so I didn't add any new dependencies. All of the vulnerable dependencies in the report come from the Spring Boot starters that were already in the original pom.xml, which means the refactoring didn't introduce any new vulnerabilities.

**What resources, tools, or coding practices did you use that might be helpful in future assignments or tasks?**

The tools I'll keep using are the OWASP dependency-check Maven plugin (with an NVD API key, and a suppression file to filter false positives), the Java Keytool for generating certificates, and Java's built-in security classes like MessageDigest. Third-party libraries and dependencies can be a big threat as they add another "puzzle-piece" that needs to be monitored, so an industry standard is to minimize the use of external libraries where possible. I also learned that dependency checking needs to be an ongoing part of the build rather than a one-time cleanup.

**Employers sometimes ask for examples of work that you have successfully completed to show your skills, knowledge, and experience. What might you show future employers from this assignment?**

I’d show the Practices for Secure Software Report, Word document in this repository. It shows that I can look at an existing application, find vulnerabilities and refactor it to fix them, such as enabling HTTPS and adding a SHA-256 checksum to verify the data, as well as performing a manual code review to make sure I didn’t introduce any new vulnerabilities, all documented in a report for a client.

## Contact
Uri Naor
