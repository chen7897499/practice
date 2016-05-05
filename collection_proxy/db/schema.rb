# encoding: UTF-8
# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# Note that this schema.rb definition is the authoritative source for your
# database schema. If you need to create the application database on another
# system, you should be using db:schema:load, not running all the migrations
# from scratch. The latter is a flawed and unsustainable approach (the more migrations
# you'll amass, the slower it'll run and the greater likelihood for issues).
#
# It's strongly recommended to check this file into your version control system.

ActiveRecord::Schema.define(:version => 20160505142014) do

  create_table "grades", :force => true do |t|
    t.integer  "student_id"
    t.integer  "score"
    t.string   "class_name"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  add_index "grades", ["student_id"], :name => "index_grades_on_student_id"

  create_table "students", :force => true do |t|
    t.string   "name"
    t.integer  "graduating_year"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

end
