extends CharacterBody2D

signal health_changed
signal dead

@export var Bullet: PackedScene
@export var speed: int
@export var rotation_speed: float
@export var gun_cooldown: float
@export var health: int

var tank_velocity = Vector2()
var can_shoot = true
var alive = true

func control(delta):
	pass

func _physics_process(delta):
	if not alive:
		return
	control(delta)
	velocity = tank_velocity
	move_and_slide()
