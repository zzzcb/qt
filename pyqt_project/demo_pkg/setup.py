from setuptools import setup, find_packages

setup(
    name="demo_pkg",
    version="0.0.1",
    packages=find_packages("src"),  # 包在src下
    package_dir={"": "src"}, # 包在src下
    package_data={
        "":["*.xml"],           # 所有包中的xml
        "widget":["*.json"],    # widget包中的json
        "widget.widget2":["*.txt"], # widget.widget2包中的txt
    },
    entry_points={
        "console_scripts":[
            "zcb = widget.widget2.a2:test_a2",
        ],
        "zxxx": (   # 生成插件
            'example = widget.widget2',
            'example2 = widget.widget2.a2',
        ),
    }
)
