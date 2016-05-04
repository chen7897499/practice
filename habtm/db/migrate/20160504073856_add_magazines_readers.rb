class AddMagazinesReaders < ActiveRecord::Migration
  def change
  	create_table :magazines_readers, :id => false do |t|
  		t.integer :magazine_id
  		t.integer :reader_id
  	end
  end

end
