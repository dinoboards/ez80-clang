
## Release Process

1. Ensure a successful build on main
2. run `git tag -l` to find the latest tags
3. Update the version referenced in the readme file*
4. create a new commit and tag for release (eg: v0.0.13-rc.103)
5. `git push && git push --tags`
5. Wait for release to be created
6. TEST: Install the release as per the readme and verify

> Also update downstream repos to now use this new release, once built

