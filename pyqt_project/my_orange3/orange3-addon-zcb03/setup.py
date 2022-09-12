from setuptools import setup


setup(
    name="ZCBName", # pip list name 
    packages=["zcbpkg"], # pkg name 
    entry_points={
        # entry point        anytext = path
        "orange.widgets": ("anytext = zcbpkg",)
    },
)