{
  "targets": [
    {
      "target_name": "gifster",
      "sources": [ "gifster.cc" ],
      "libraries": [ "/Users/appfolio/dev/gifski/target/release/libgifski.a" ],
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
