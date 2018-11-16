{
  "targets": [
    {
      "target_name": "gifster",
      "sources": [ "gifster.cc" ],
      "libraries": [ "/Volumes/Vault/Projects/warhol/lib/libgifski.a" ],
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
