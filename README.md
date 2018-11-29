# eos-torrent
Never lose those magnet links ever again. I am not responsible for anything that is done with this contract.

## What is this?
This contract will let users store data on the EOS Blockchain for 'magnet' links. It's incredibly simple and has an add or remove function only.

```
cleos push action contract_account create '["username", "torrent title", "torrent magnet", "md5hash"]' -p username
```

```
cleos push action contract_acccount remove '["username", id]' -p username
```
