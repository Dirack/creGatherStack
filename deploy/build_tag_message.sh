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
echo "VERSION $CURRENT_TAG"

# TAG MESSAGE 
echo "## Added"
git log HEAD..."$PREVIOUS_TAG" --grep='^\[ADD\]' --pretty='format:(%h) %s%n%b%n'
echo "## Changed"
git log HEAD..."$PREVIOUS_TAG" --grep='^\[CHA\]' --pretty='format:(%h) %s%n%b%n'
echo "## Deprecated"
git log HEAD..."$PREVIOUS_TAG" --grep='^\[DEP\]' --pretty='format:(%h) %s%n%b%n'
echo "## Removed"
git log HEAD..."$PREVIOUS_TAG" --grep='^\[REM\]' --pretty='format:(%h) %s%n%b%n'
echo "## Fixed"
git log HEAD..."$PREVIOUS_TAG" --grep='^\[FIX\]' --pretty='format:(%h) %s%n%b%n'
echo "## Security"
git log HEAD..."$PREVIOUS_TAG" --grep='^\[SEC\]' --pretty='format:(%h) %s%n%b%n'

