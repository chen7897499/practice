json.array!(@images) do |image|
  json.extract! image, :id, :name, :picture
  json.url image_url(image, format: :json)
end
