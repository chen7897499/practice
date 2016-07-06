module PeopleHelper
	def cache_key_for_person
		count = Person.count
		max_update_at = Person.maximum(:updated_at).try(:utc).try(:to_s, :number)
		"people/all-#{count}-#{max_update_at}"
	end
end
