# This Python file uses the following encoding: utf-8

import os

class FileManager:
    def __init__(self, file_path):
        self.file_path = file_path
        self.abs_path = os.path.abspath(self.file_path)

    def write(self, line):
        with open(self.abs_path, "w", encoding="utf-8") as f:
            f.write(line + "\n")

    def readAll(self):
        result = []
        with open(self.abs_path, "r", encoding="utf-8") as f:
            for line in f:
                result.append(line.strip())
