extends Control


var manager: GdSerialManager

var data_string: String
var data_array: Array

var button_state: int = 1

var k_value:float

func _ready() -> void:
	manager = GdSerialManager.new()
	manager.data_received.connect(_on_data)
	manager.port_disconnected.connect(_on_disconnected)
	
	if manager.open("COM4", 115200, 1000, 0):
		print("Connected sucessfully")


func _process(_delta: float) -> void:
	manager.poll_events()


func _on_data(port: String, data: PackedByteArray) -> void:
	print("Data from", port, ":", data.get_string_from_utf8())
	data_string = data.get_string_from_utf8().strip_edges()
	if data_string.is_valid_int():
		button_state = int(data_string)
	elif data_string.is_valid_float():
		k_value = float(data_string)
	print("k_value:", k_value, " button state:", button_state)


func _on_disconnected(port: String) -> void:
	print("Lost connection to ", port)
