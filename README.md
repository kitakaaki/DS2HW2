# 🚀 Git & GitHub Essentials: The Survival Guide

This guide covers the fundamental workflow for collaborating on projects using Git and GitHub.

---

## 1. Setting Up
First, get the code from GitHub onto your local machine.

| Command | Description |
| :--- | :--- |
| `git clone <url>` | Downloads the repository to your computer. |
| `git remote -v` | Shows the online URL your local repo is linked to. |

---

## 2. Working on Features (Branching)
**Rule #1:** Never work directly on `main`. Always create a feature branch.

* **Create a branch:** `git branch <branch-name>`
* **Switch to a branch:** `git switch <branch-name>`
* **Create & Switch (Shortcut):** `git checkout -b <branch-name>`

---

## 3. Saving Changes
Think of this as "Staging" (the box) and "Committing" (sealing the box).

1. **Check status:** `git status` (Do this often!)
2. **Stage files:** `git add <file-name>` or `git add .` to add all.
3. **Commit:** `git commit -m "Brief description of changes"`

---

## 4. Staying Synced
Before you push your work, make sure you have the latest code from your team.

* **`git fetch`**: Downloads updates from GitHub but doesn't change your files yet.
* **`git pull`**: Downloads updates and merges them into your current branch immediately.

---

## 5. Sharing & Reviewing (The GitHub Flow)

### Step 1: Push to GitHub
Send your local branch to the cloud:
`git push origin <branch-name>`

### Step 2: Create a Pull Request (PR)
* This happens on **GitHub.com**.
* Navigate to the repository; click the **"Compare & pull request"** button.
* Describe your changes and request a review.

### Step 3: Accept/Merge a PR
* On the PR page in GitHub, after the code is reviewed, click **"Merge pull request"**.
* This joins your feature branch into the `main` branch.

---

## 6. Cleanup & Advanced Merging
Once the code is merged on GitHub, you need to update your local `main`.

* **`git merge <branch>`**: Joins two branches together.
* **`git rebase main`**: Moves your feature commits to the "tip" of the main branch for a cleaner history.

> **💡 Pro-Tip:** If you get stuck, type `git status`. It usually tells you exactly how to fix the current situation!
