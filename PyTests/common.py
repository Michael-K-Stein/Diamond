import os


def get_test_resources_dir():
    return os.path.join(os.path.dirname(__file__), "..", "CTests", "Resources")
