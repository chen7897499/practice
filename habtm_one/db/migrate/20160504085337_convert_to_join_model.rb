class ConvertToJoinModel < ActiveRecord::Migration
  def up
  	drop_table :magazines_readers
  	create_table :subscriptions do |t|
  		t.column :reader_id, :integer
  		t.column :magazine_id, :integer
  		t.column :last_renewal_on, :date
  		t.column :length_in_issues, :integer
  	end
  end

  def down
  end
end
