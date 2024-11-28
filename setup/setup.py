from setuptools import setup, find_packages
import platform

setup(
    name="pydia3",
    version="0.0.1",
    description="Python interface for Microsoft's Debug Interface Access (DIA) SDK.",
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
    author="Michael K. Steinberg",
    author_email="m.kuper.steinberg@gmail.com",
    url="https://github.com/Michael-K-Stein/pydia",
    license="MIT",  # Update with your license
    packages=["pydia"],  # Use the internal module name here
    package_data={
        "pydia": ["*.pyd"],
    },
    include_package_data=True,  # Include non-Python files
    classifiers=[
        "Programming Language :: Python :: 3",
        "Operating System :: Microsoft :: Windows",
    ],
    python_requires=">=3.12",
)
