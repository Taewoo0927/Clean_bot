# Git.mk

# To do:
# Make git-init to set up name & email to push properly
git-init:
	@git config user.name "Taewoo0927";
	@git config user.email "taewookim0927@gmail.com";

# Check if there is uncommitted changes
git-check: init
	@if ! git diff-index --quiet HEAD --; then \
		echo "Uncommitted changes detected. Please commit your changes before proceeding."; \
		exit 1; \
	fi

# Pull request
git-pull:
	@if git fetch && [ -z "$$(git log HEAD..origin/$$(git rev-parse --abbrev-ref HEAD) --oneline)" ]; then \
		echo "Your branch is already up to date."; \
	else \
		echo "Pulling latest changes from the remote branch..."; \
		git pull origin $$(git rev-parse --abbrev-ref HEAD); \
		echo "Successfully pulled the latest changes."; \
	fi

# Commit the changes
git-commit:
	@echo "Enter commit message:"; \
	read msg; \
	if [ -z "$$msg" ]; then \
		msg="Auto-commit from Makefile"; \
	fi; \
	git add .; \
	git commit -m "$$msg"; \
	echo "Changes have been committed with message: '$$msg'."

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
git-pull-commit-push: git-pull git-check-commit git-push
	@echo "Pull, commit, and push completed successfully."