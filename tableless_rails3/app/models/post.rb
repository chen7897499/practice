binding.pry

class Post
	include ActiveModel::Validations
	include ActiveModel::Conversion
	extend ActiveModel::Naming

  attr_accessor :body

  validates_presence_of :body

  def persisted?
  	false
  end

  def initialize(attributes={})
  	attributes && attributes.each do |name, value|
  		send("#{name}=", value) if respond_to? name.to_sym
  	end
  end
end
