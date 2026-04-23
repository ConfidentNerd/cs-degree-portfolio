# Software Testing, Automation, and Quality Assurance (CS 320)

A Java-based contact management service built to practice software testing, defensive programming and achieve high test coverage using JUnit.

---

## Project Reflection

**How can I ensure that my code, program, or software is functional and secure?**
I can ensure my code is functional and secure, by utilizing a defensive programming approach, where I make sure to always validate inputs before allowing them to influence the program itself. For example in this program inside the constructor, if the passed ID was invalid, I’d throw an exception immediately. By taking this approach and making sure to throughly test the program with both expected and unexpected cases, I can make sure I'm writing functional and secure code.

**How do I interpret user needs and incorporate them into a program?**
I interpret user needs first by making sure I understand them well. My reasoning is that understanding the problem is most important as it makes sure we aren't working on the wrong thing, so I ask a lot of questions and do my best to understand their requirements. Afterwards I continue by translating them into explicit software requirements. Then (depending on how complex is the issue), I take a Test Driven Development (TDD) approach where I translate those requirements into tests. This makes the actual coding and development a lot smoother as I can see in real time if my program answers the requirements from the user.

**How do I approach designing software?**
I approach software design by making sure to take the time to make the right choices that lead to better efficiency, maintainability and longevity. For example, I ensured my code was efficient by choosing a data structure that fits well for the job. I went with a HashMap because it offers a highly optimized time efficiency for lookups, insertions, and deletions. Beyond that I do my best to write good tests. While it might be slow, annoying and tedious at the time, I believe the discipline to write tests is critical. By taking the hard route today, I make sure to set myself up for the easy route later.