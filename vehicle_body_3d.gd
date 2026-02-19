extends VehicleBody3D

@export var Max_Steer = 0.9
@export var Engine_Power = 300
@onready var root = $".."
# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


func _physics_process(delta: float) -> void:
	steering = move_toward(steering, root.k_value * Max_Steer, delta * 10)
	engine_force = (1 - root.button_state ) * Engine_Power
