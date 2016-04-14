class CreateQuestions < ActiveRecord::Migration
  def change
    create_table :questions do |t|
      t.string :ask
      t.references :member

      t.timestamps
    end
    add_index :questions, :member_id
  end
end
