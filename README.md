<h1 align="center" style="animation: slideIn 1.5s ease-in-out;">ASK FM System</h1>
<h3 align="center" style="animation: fadeIn 2s ease-in-out;">🚀 A Simple Q&A Platform for Asking and Answering Questions 🚀</h3>

<p align="center" style="animation: fadeIn 2s ease-in-out;"> 
  <img src="https://komarev.com/ghpvc/?username=askfm&label=Project%20views&color=0e75b6&style=flat" alt="askfm" /> 
</p>

---

<h3 align="center" style="animation: fadeIn 2s ease-in-out;">📖 About the Project</h3>
<p align="center" style="animation: fadeIn 2s ease-in-out;">
  The <strong>ASK FM System</strong> is a console-based Q&A platform where users can register, log in, ask questions, answer questions, and view their feed. It supports anonymous questions and threaded conversations, making it a simple yet powerful tool for interaction.
</p>

---

<h3 align="center" style="animation: fadeIn 2s ease-in-out;">✨ Features</h3>
<p align="center" style="animation: fadeIn 2s ease-in-out;">
  ✅ <strong>User Registration & Login</strong>: Create an account and log in securely.<br>
  ✅ <strong>Ask Questions</strong>: Ask questions to other users (optionally anonymously).<br>
  ✅ <strong>Answer Questions</strong>: Answer questions directed to you.<br>
  ✅ <strong>View Feed</strong>: See all questions and answers in your feed.<br>
  ✅ <strong>Delete Questions</strong>: Remove questions you've asked.<br>
  ✅ <strong>List Users</strong>: View all registered users.<br>
</p>

---

<h3 align="center" style="animation: fadeIn 2s ease-in-out;">📂 File Structure</h3>
<p align="center" style="animation: fadeIn 2s ease-in-out;">
  <strong>Account.txt</strong>: Stores user account information.<br>
  <strong>Questions.txt</strong>: Stores questions asked by users.<br>
  <strong>Answers.txt</strong>: Stores answers to questions.<br>
  <strong>Configuration.cpp/h</strong>: Manages system configuration.<br>
  <strong>main.cpp</strong>: Entry point of the application.<br>
  <strong>Questions.cpp/h</strong>: Manages questions and their properties.<br>
  <strong>Users.cpp/h</strong>: Manages user information.<br>
  <strong>Answer.cpp/h</strong>: Manages answers to questions.<br>
</p>

---

<h3 align="center" style="animation: fadeIn 2s ease-in-out;">🚀 How to Run</h3>
<p align="center" style="animation: fadeIn 2s ease-in-out;">
  1. <strong>Compile the Code</strong>: Use a C++ compiler (e.g., <code>g++</code>).<br>
  ```bash
  g++ main.cpp Configuration.cpp Answer.cpp Questions.cpp Users.cpp -o askfm
