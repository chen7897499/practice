class Magazine < ActiveRecord::Base
	has_many :subscriptions
	has_many :readers, :through => :subscriptions
	has_many :semiannual_subscribers,
	         :through => :subscriptions,
	         :source => :reader,
	         :conditions => ['length_in_issues = 6']
end
