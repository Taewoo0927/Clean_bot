# Git.mk

# Check if there is uncommitted changes
check-git:
	@if ! git diff-index --quiet HEAD --; then \
		echo "Uncommitted changes detected. Please commit your changes before proceeding."; \
		exit 1; \

# Pull request
git-pull:
	@git pull origin $$(git rev-parse --abrev-ref HEAD)
	@echo "Pulled lastest changes from the remote branch"

# Commit the changes
git-commit:
	@echo "Enter commit message:" \
	read msg; \
	git add .; \
	git commit -m "$$msg"
	@echo "Changes have been committed."

# Check if there is uncommited changes and commit the changes
git-check-commit:
	@git config user.name "Taewoo0927"
	@git config user.email "taewookim0927@gmail.com"
	@if ! git diff-index --quiet HEAD --; then \
		echo "Uncommitted changes detected. Auto-committing changes..."; \
		git add .; \
		echo "Enter commit message (or press Enter for default message):"; \
		read msg; \
		if [ -z "$$msg" ]; then \
			msg="Auto-commit from Makefile"; \
		fi; \
		git commit -m "$$msg"; \
		echo "Changes have been committed with message: '$$msg'."; \
	else \
		echo "No changes to commit."; \
	fi
# Push the committed changes
git-push:
	@git push origin $$(git rev-parse --abbrev-ref HEAD)
	@echo "Pushed changes to the remote repository."

# Pull, Commit, and Push in one go
git-pull-commit-push: git-pull git-commit git-push
	@echo "Pull, commit, and push completed successfully."