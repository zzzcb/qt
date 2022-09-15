"""
配合setup.py 使用
"""
import pkg_resources

ENTRY_POINT = "orange.widgets"
entry_points_iter = pkg_resources.iter_entry_points(ENTRY_POINT)
for entry_point in entry_points_iter:
	print(entry_point.name)      # setup.py 中的 k
	print(entry_point.dist)		 # 版本信息
	print(entry_point.resolve()) # module object 模块对象 
