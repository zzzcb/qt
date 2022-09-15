from setuptools import setup

setup(
    name="zcbpkg",  # pip list name
    packages=["zcbpkg"],  # package name
    entry_points={
        "orange.widgets": ["any_text = zcbpkg",]
    }
)
