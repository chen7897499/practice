class CreatePosts < ActiveRecord::Migration
  def change
    create_table :posts do |t|
      t.string :title
      t.text :body
      t.references :member

      t.timestamps
    end
    add_index :posts, :member_id
  end
end
