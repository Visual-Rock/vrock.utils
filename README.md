# Utils

- [List\<T\>](./include/vrock/utils/List.md)

## meson

create a file with the name `vrockutils.wrap`
and fill it with the following content

```text
[wrap-git]
url=https://github.com/Visual-Rock/vrock.utils
revision=head
depth=1

[provide]
vrockutils=vrockutils_dep
```