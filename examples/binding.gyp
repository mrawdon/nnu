{
  "targets": [
    {
      "target_name": "nnu-example",
	  "include_dirs" : [
        "<!(node -e \"require('nan')\")",
        ".."
      ],
      "sources": [
        "main.cpp"
      ]
    }
  ]
}
