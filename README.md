# passt-bin
Prebuilt binaries of [passt](https://passt.top/) built with `zig cc`.

| Target | Minimum glibc |
| --- | --- |
| `x86_64-linux-gnu` | 2.28 |
| `aarch64-linux-gnu` | 2.28 |

Each release asset is a tarball laid out for `/usr/local`:

```
bin/passt
bin/passt.avx2   (x86_64 only)
bin/pasta -> passt
bin/pasta.avx2   (x86_64 only)
bin/passt-repair
bin/pesto
share/man/man1/*.1
share/doc/passt/*
```

The minimum glibc follows the oldest supported release of Ubuntu, Debian and RHEL (RHEL 8 as of 2026-10).
The binaries are dynamically linked against glibc, so `--runas` accepts user and group names (NSS lookups work).
`PAGE_SIZE` is fixed at build time to 4096.

# About release workflow
Releases are tagged with the date of the passt tag in SemVer form, such as `v2026.10.2` for `2026_10_02.cba3570`.

Renovate updates `version.json` when passt tags a new release.
When the update is merged, CI on the main branch builds the binaries and creates the release, unless the tag already exists.
To build another passt version, run the CI workflow manually with `build-version`.

```console
$ gh workflow run ci -f build-version=2026_10_02.cba3570
```
