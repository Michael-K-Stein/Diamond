import pytest
import pydia
from pydia import DataSource


def test_datasource_creation():
    data_source = DataSource()
    assert data_source