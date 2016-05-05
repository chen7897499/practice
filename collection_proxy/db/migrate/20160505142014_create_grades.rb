class CreateGrades < ActiveRecord::Migration
  def change
    create_table :grades do |t|
      t.belongs_to :student
      t.integer :score
      t.string :class_name

      t.timestamps
    end
    add_index :grades, :student_id
  end
end
