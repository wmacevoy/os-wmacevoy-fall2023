#!/usr/bin/env python3

import json


def write_config():
  config = {"key1": "value1", "key2": "value2"}
  try:
      file = open("example.txt", "w")
      json.dump(config, file)
      return config
  except FileNotFoundError:
    print("File not found.")
  except IOError:
    print("An IOError occurred.")
  finally:
    print("Closing file.")
    file.close()

write_config()
