#!/bin/bash
#
# - ADD Added for new features.
# - CHA Changed for changes in existing functionality.
# - DEP Deprecated for once-stable features removed in upcoming releases.
# - REM Removed for deprecated features removed in this release.
# - FIX Fixed for any bug fixes.
# - SEC Security to invite users to upgrade in case of vulnerabilities.

PREVIOUS_TAG=$(git tag | sort -n -r | head -1)
CURRENT_TAG=$(cat VERSION.md)

# TAG HEADER
echo "VERSION $CURRENT_TAG" > tag.deploy

# TAG MESSAGE 
echo "## Added" >> tag.deploy
git log HEAD..."$PREVIOUS_TAG" --grep='^\[ADD\]' --pretty='format:(%h) %s%n%b%n' >> tag.deploy
echo "## Changed" >> tag.deploy
git log HEAD..."$PREVIOUS_TAG" --grep='^\[CHA\]' --pretty='format:(%h) %s%n%b%n' >> tag.deploy
echo "## Deprecated" >> tag.deploy
git log HEAD..."$PREVIOUS_TAG" --grep='^\[DEP\]' --pretty='format:(%h) %s%n%b%n' >> tag.deploy
echo "## Removed" >> tag.deploy
git log HEAD..."$PREVIOUS_TAG" --grep='^\[REM\]' --pretty='format:(%h) %s%n%b%n' >> tag.deploy
echo "## Fixed" >> tag.deploy
git log HEAD..."$PREVIOUS_TAG" --grep='^\[FIX\]' --pretty='format:(%h) %s%n%b%n' >> tag.deploy
echo "## Security" >> tag.deploy
git log HEAD..."$PREVIOUS_TAG" --grep='^\[SEC\]' --pretty='format:(%h) %s%n%b%n' >> tag.deploy

